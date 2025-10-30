import argparse
import numpy as np

from aie.extras.context import mlir_mod_ctx
from aie.dialects.aie import tile, AIEDevice, device
import aie.utils.trace as trace_utils
from aie.iron.dtype import str_to_dtype


# The following microkernels have to be determined using some method
# f

microkernel_mac_dim_map = {
    "npu": {
        "bf16": (4, 8, 4),
        "i8": (4, 8, 8),
        "i16": (4, 4, 4),
    },
    "npu2": {
        "bf16": {
            # emulate_bf16_mmul_with_bfp16
            True: (8, 8, 8),
            False: (4, 8, 8),
        },
        "i8": (8, 8, 8),
        "i16": (4, 4, 8),
    },
}

def main():
    argparser = argparse.ArgumentParser(prog="matmul single core")
    argparser.add_argument("--dev", type=str, choices=["npu", "npu2"], default="npu")

    argparser.add_argument('-M', type=int, default=256)
    argparser.add_argument('-K', type=int, default=256)
    argparser.add_argument('-N', type=int, default=256)

    argparser.add_argument('-m', type=int, default=64)
    argparser.add_argument('-k', type=int, default=64)
    argparser.add_argument('-n', type=int, default=64)

    argparser.add_argument("--dtype_in", type=str, choices=["bf16", "i8", "i16"], default="i16")
    argparser.add_argument("--dtype_out", type=str, choices=['bf16', 'i8', 'i16', 'f32', 'i32'], default='i32')

    argparser.add_argument("--b-col-maj", type=int, choices=[0, 1], default=0)
    argparser.add_argument("--emulate-bf16-mmul-with-bfp16", type=bool, default=False)
    argparser.add_argument("--trace_size", type=int, default=0)

    args = argparser.parse_args()

    with mlir_mod_ctx() as ctx:
        custom_matmul(
            args.dev,
            args.M,
            args.K,
            args.N,
            args.m,
            args.k,
            args.n,
            args.dtype_in,
            args.dtype_out,
            args.b_col_maj,
            args.emulate_bf16_mmul_with_bfp16,
            args.trace_size
        )
        print(ctx.module)


@iron.jit(placed=True)
def custom_matmul(
        dev, M, K, N, m, k, n, dtype_in_str, dtype_out_str, b_col_maj, emulate_bf16_mmul_with_bfp16, trace_size
):
    assert M % m == 0
    assert K % k == 0
    assert K % n == 0

    mac_dims = microkernel_mac_dim_map[dev][dtype_in_str]
    if dev == "npu2" and dtype_in_str == "bf16":
        r, s, t = mac_dims[emulate_bf16_mmul_with_bfp16]
    else:
        r, s, t = mac_dims

    assert m % r == 0
    assert k % s == 0
    assert n % t == 0

    vectorized = True
    enable_tracing = True if trace_size > 0 else False

    dtype_in = str_to_dtype(dtype_in_str)
    dtype_out = str_to_dtype(dtype_out_str)

    assert np.issubdtype(dtype_in, np.integer) == np.issubdtype(
        dtype_out, np.integer
    ), f"Input dtype ({dtype_in}) and output dtype ({dtype_out}) must either both be integral or both be float"
    assert (
            np.dtype(dtype_out).itemsize >= np.dtype(dtype_in).itemsize
    ), f"Output dtype ({dtype_out}) must be equal or larger to input dtype ({dtype_in})"

    A_sz = M * K
    B_sz = K * N
    C_sz = M * N

    M_div_m = M // m
    K_div_k = K // k
    N_div_n = N // n
    tiles = M_div_m * N_div_n

    k_x_N = k * N
    m_x_N = m * N

    C_sz_in_bytes = C_sz * np.dtype(dtype_out).itemsize

    A_taps = []
    B_taps = []
    C_taps = []

    if dev == "npu":
        dev_ty = AIEDevice.npu1_1col
    else:
        dev_ty = AIEDevice.npu2

    @device(dev_ty)
    def device_body():
        a_ty = np.ndarray[(m,k), np.dtype[dtype_in]]
        b_ty = np.ndarray[(k,n), np.dtype[dtype_in]]
        c_ty = np.ndarray[(m,k), np.dtype[dtype_in]]

if __name__ == '__main__':
    main()