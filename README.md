# Robocup game controller client

## Overview

This simple client allows to receive messages from game controller server and
sent alive and manual penalize messages back.

You can find usage example in appropriate folder. This client is developed for
Darwin OP but it can work in another hardware. Also you can change
game_control_data_t structure to another version of this structure and it would
be working fine. 

## Requires

Compiler with c++14 support needed.

The client uses Boost::Asio library for network communication.

## Build and run

Clone repository:
```
   git clone https://github.com/arssivka/robocup-game-controller-client
```

Unix, MacOS:

```
   mkdir -p robocup-game-controller-client/build
   cd robocup-game-controller-client/build
   cmake --CMAKE_BUILD_TYPE=Release -DGC_CLIENT_BUILD_EXAMPLE=ON ..
   make -j4
```

Launch example
```
   ./example
```


## License
Project sources distributed under [MIT license](https://github.com/arssivka/robocup_gamectrl/blob/master/LICENSE).
