### jsoncons::jsonschema::evaluation_options

```cpp
#include <jsoncons_ext/jsonschema/jsonschema.hpp>

class evaluation_options;
```

<br>

Specifies options for evaluating JSON Schema documents.

#### Constructors

    evaluation_options()
Constructs an `evaluation_options` with default values. 

#### Members

    const std::string& default_version() const;
    evaluation_options& default_version(const std::string& version); 
Get or set a default [schema dialect](schema_dialect.md). The default
schema dialect determines which version of JSON Schema is used if the `$schema` 
keyword is not present in the top level of the JSON Schema document. 
Defaults to `schema::draft202012()`.

    bool compatibility_mode() const;
    evaluation_options& compatibility_mode(bool value); 
Get or set the compatibility mode. If set to `true`, the JSON Schema 2019-09
and 2020-12 implementations support the Draft 7 "definitions" and 
"dependencies" keywords. The default is `false`. 

    bool require_format_validation() const;
    evaluation_options& require_format_validation(bool value); 
Determines whether `format` is an assertion. The default is `false`. 

