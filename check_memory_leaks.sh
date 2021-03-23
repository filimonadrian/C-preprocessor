#/bin/bash

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
#	 ./$1 -Dbere

         ./$1 -D constanta=litoral -Dmare=munte -Dbere -I Documents -IDownloads test_file.in -o output_file
