#pragma once

#ifndef AIECAD_IMPL_COPY_AND_MOVE_CTORS
#   define AIECAD_IMPL_COPY_AND_MOVE_CTORS(Type, RHS) \
        Type(const Type&) = RHS;                     \
        Type(Type&&) = RHS;
#endif

#ifndef AIECAD_IMPL_COPY_AND_MOVE_OVERLOADS
#   define AIECAD_IMPL_COPY_AND_MOVE_OVERLOADS(Type, RHS) \
        Type& operator=(const Type&) = RHS;              \
        Type& operator=(Type&&) = RHS;
#endif

#ifndef AIECAD_DELETE_COPY_AND_MOVE
#   define AIECAD_DELETE_COPY_AND_MOVE(Type)  \
        AIECAD_IMPL_COPY_AND_MOVE_CTORS(Type, delete)  \
        AIECAD_IMPL_COPY_AND_MOVE_OVERLOADS(Type, delete)
#endif

#ifndef AIECAD_DEFAULT_COPY_AND_MOVE
#   define AIECAD_DEFAULT_COPY_AND_MOVE(Type)  \
        AIECAD_IMPL_COPY_AND_MOVE_CTORS(Type, default)  \
        AIECAD_IMPL_COPY_AND_MOVE_OVERLOADS(Type, default)
#endif


