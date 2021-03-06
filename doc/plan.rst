Development plan
================

To-Do
-----

* Document examples
* `Check Hawkmoth errors from this issue <https://github.com/jnikula/hawkmoth/issues/21>`_
* Check if unused commands don't influence the parsing (244, 245, 249, 253)
* Add an `architecture description <https://matklad.github.io/2021/02/06/ARCHITECTURE.md>`_
* Check how logging header functions, check if library can be used on different platforms
* Check if it's possible to feed "bytes_to_data" malformed values (probably not, because note byte has a fixed range of values)
* Check if there is a point in moving **midi_message_state_t** and **midi_message_parser_t**

Done
----

* Reconsider header file naming, "midi" word repeats several times
* Document the sources
