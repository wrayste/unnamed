#pragma once

// MSVC HACK - Undefine stupid MS macros
#undef min
#undef max

// IWYU pragma: begin_exports
#include <exception> // for exception
#include <iosfwd>    // for string
#include <memory>    // for unique_ptr
#include <utility>   // for pair
#include <vector>    // for vector

#include "rapidcheck/gen/Arbitrary.h"
#include "rapidcheck/gen/Build.h"
#include "rapidcheck/gen/Chrono.h"
#include "rapidcheck/gen/Container.h"
#include "rapidcheck/gen/Create.h"
#include "rapidcheck/gen/Exec.h"
#include "rapidcheck/gen/Maybe.h"
#include "rapidcheck/gen/Numeric.h"
#include "rapidcheck/gen/Predicate.h"
#include "rapidcheck/gen/Select.h"
#include "rapidcheck/gen/Text.h"
#include "rapidcheck/gen/Text.hpp"
#include "rapidcheck/gen/Transform.h"
#include "rapidcheck/gen/Tuple.h"

#include "rapidcheck/detail/Any.hpp"
#include "rapidcheck/detail/Results.h"
#include "rapidcheck/detail/Variant.hpp"

#include "rapidcheck/seq/Create.h"
#include "rapidcheck/seq/Operations.h"
#include "rapidcheck/seq/SeqIterator.h"
#include "rapidcheck/seq/Transform.h"
#include "rapidcheck/seq/Transform.hpp"

#include "rapidcheck/shrink/Shrink.hpp"

#include "rapidcheck/shrinkable/Create.h"
#include "rapidcheck/shrinkable/Operations.h"
#include "rapidcheck/shrinkable/Transform.h"
#include "rapidcheck/shrinkable/Transform.hpp"

#include "rapidcheck/Assertions.h"
#include "rapidcheck/Check.h"
#include "rapidcheck/Check.hpp"
#include "rapidcheck/Classify.h"
#include "rapidcheck/Gen.h"
#include "rapidcheck/Gen.hpp"
#include "rapidcheck/GenerationFailure.h"
#include "rapidcheck/Log.h"
#include "rapidcheck/Maybe.h"
#include "rapidcheck/Maybe.hpp"
#include "rapidcheck/Seq.h"
#include "rapidcheck/Seq.hpp"
#include "rapidcheck/Show.h"
#include "rapidcheck/Show.hpp"
#include "rapidcheck/Shrinkable.h"
// IWYU pragma: end_exports
