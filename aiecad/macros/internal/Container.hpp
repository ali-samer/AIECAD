#pragma once

#ifndef AIECAD_IMPL_COPY_OVERLOADS
#	define AIECAD_IMPL_COPY_OVERLOADS(Container, RHS) \
		Container& operator=(const Container&) = RHS; \
		Container& operator=(Container&&) = RHS;
#endif // AIECAD_IMPL_COPY_OVERLOADS

#ifndef AIECAD_IMPL_COPY_CONSTRUCTORS
#	define AIECAD_IMPL_COPY_CONSTRUCTORS(Container, RHS) \
		Container(const Container&) = RHS; \
		Container(Container&&) = RHS;
#endif

#ifndef AIECAD_DISABLE_COPY_ASSIGNMENTS
#	define AIECAD_DISABLE_COPY_ASSIGNMENTS(Container) \
		AIECAD_IMPL_COPY_OVERLOADS(Container, delete) \
		AIECAD_IMPL_COPY_CONSTRUCTORS(Container, delete)
#endif

#ifndef AIECAD_DISABLE_COPY_OVERLOADS
#	define AIECAD_DISABLE_COPY_OVERLOADS(Container) \
		AIECAD_IMPL_COPY_OVERLOADS(Container, delete)
#endif // AIECAD_DISABLE_COPY_OVERLOADS

#ifndef AIECAD_DEFAULT_COPY_OVERLOADS
#	define AIECAD_DEFAULT_COPY_OVERLOADS(Container) \
		AIECAD_IMPL_COPY_OVERLOADS(Container, default)
#endif // AIECAD_DEFAULT_COPY_OVERLOADS