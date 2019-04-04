# Micro Edge Client

This client is not designed to be a one-size-fits-all project. It's main goal is basically to be a library to allow setting up and managing various IPSO-based sensors, however it does not do any of the reading and sending of this data by itself. Instead, it provides the framework to do so, and each embedded target can provide the actual libraries to be used. This allows the MEC to work on any small embedded device without needing to deal with the intricacies of every possible device.
