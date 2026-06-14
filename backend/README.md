# Backend

Since each platform boots differently, we need an abstraction to deal with this
complexity. A backend is code that gets executed right after the platform gives
control to the bootloader, and it exposes an API common among all backends (core
API).
