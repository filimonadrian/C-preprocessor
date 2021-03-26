#/bin/bash

NR_RUNS=1000 # How many times to run

	for ((i = 0; i < $NR_RUNS; i++)); do
#		LD_PRELOAD="./libso.so" $EXEC_NAME $params $input_f > $out_f
		LD_PRELOAD="./libso.so" ./so-cpp -D DEBUG=1 -D CUSTOM_DBG=custom-debugging -I _test/inputs/test38.dir ./_test/inputs/test38.in > output_38
		echo $?
	done



