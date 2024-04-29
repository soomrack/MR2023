### jsoncons::jsonschema::validation_message

```cpp
#include <jsoncons_ext/jsonschema/jsonschema_error.hpp>
```

<br>

`jsoncons::jsonschema::validation_message` defines a message type for reporting failures in jsonschema operations.

#### Member functions

    const jsonpointer::json_pointer& instance_location() const;
The location of the JSON value within the instance being validated,
expressed as a URI fragment-encoded JSON Pointer.

    const std::string& message() const;
An error message that is produced by the validation.

    const jsonpointer::json_pointer& eval_path() const;         
The relative location of the validating keyword that follows 
the validation path, expressed as a JSONPointer. 

    const jsoncons::uri& schema_path() const;   
The absolute, dereferenced location of the validating keyword,
expressed as an absolute URI using the canonical URI of the 
relevant schema.

    const std::vector<validation_message>& details() const
Returns a list of nested errors

