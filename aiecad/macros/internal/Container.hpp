#pragma once

#ifndef AIECAD_IMPL_COPY_OVERLOADS
#	define AIECAD_IMPL_COPY_OVERLOADS(Container, RHS) \
		explicit Container operator=(const Container&) = RHS; \
		explicit Container operator=(Container&&) = RHS;
#endif // AIECAD_IMPL_COPY_OVERLOADS

#ifndef AIECAD_DISABLE_COPY_OVERLOADS
#	define AIECAD_DISABLE_COPY_OVERLOADS(Container) \
		AIECAD_IMPL_COPY_OVERLOADS(Container, delete)
#endif // AIECAD_DISABLE_COPY_OVERLOADS

#ifndef AIECAD_DEFAULT_COPY_OVERLOADS
#	define AIECAD_DEFAULT_COPY_OVERLOADS(Container) \
		AIECAD_IMPL_COPY_OVERLOADS(Container, default)
#endif // AIECAD_DEFAULT_COPY_OVERLOADS