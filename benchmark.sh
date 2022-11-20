#!/bin/bash

startTime_ms=$(date +%s%3N);
algRuntime_ms=0

for i in `seq 1 $1`
do
  # ./build/HighestNumber set $2>/dev/null
  algRuntime_ms=`echo $algRuntime_ms + $(./build/HighestNumber set $2) | bc`
done

endTime_ms=$(date +%s%3N);

duration=$(($endTime_ms-$startTime_ms))
echo "Total runtime: "$duration"ms"
echo "Total algorithm runtime: "$algRuntime_ms"ms"
