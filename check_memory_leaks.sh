#/bin/bash

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
 	 ./so-cpp -D DEBUG=1 -D CUSTOM_DBG=custom-debugging -I _test/inputs/test38.dir ./_test/inputs/test38.in

