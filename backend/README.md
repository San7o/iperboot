# Backend

Since each platform boots differently, we need an abstraction to deal with this
complexity. A backend is code that gets executed right after the platform gives
control to the bootloader, and it exposes an API common among all backends (core
API).

On ARM, the very first code that gets executed depends on the architecture, such
as ARMv8 or ARMv7 unless the board runs a specific firmware before loading ours.
