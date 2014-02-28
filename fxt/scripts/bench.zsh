#! /usr/bin/env zsh

export LC_ALL=C ## for sorting
DEMOBIN=./bin

FXT_EXTRA_FLAGS='-Wno-conversion -Wno-unused'

## add options as follows:
#FXT_EXTRA_FLAGS="$FXT_EXTRA_FLAGS -march=amdfam10 -mtune=amdfam10"
#FXT_EXTRA_FLAGS="$FXT_EXTRA_FLAGS -mtune=generic"


## system name:
    uname -a
    echo
    if test -n "$CXX"; then
        $CXX --version | head -1
    else
        c++ --version | head -1
    fi
    echo

if [ -z "$PAT" ]; then
    ## full suite, incl. recompilation of the lib and CPU-info

    PAT='.'; ## this matches all files

    ## CPU info:
    cat /proc/cpuinfo
    echo -e '\n\n\n'

    ## compile the library as a benchmark:
    make clobber  &>/dev/null
    make cat  &>/dev/null
    echo "Compiling the FXT library:"
    time make -s lib FXT_EXTRA_FLAGS=${FXT_EXTRA_FLAGS}
    echo -e '\n\n\n'

else
    ## do not recompile lib when PAT was supplied:
    echo "Benchmark with PAT=[$PAT]:"
fi


## run FXT benchmarks (for all files whose filename contain the pattern PAT):
DD=$(grep -l 'BENCHARGS' demo/*/*-demo.cc demo/*/*-bench.cc | sort)
for d in ${=DD}; do  ## loop over files
#    echo " :: d=[$d]"
    if [ "${d}" \!= "${d/${PAT}/}" ]; then  ## pattern matches
        echo '------------------------------------------------------------';
        make -s  1demo DSRC=$d DEMOFLAGS='-DTIMING -DFXT_SILENT_NXARG' FXT_EXTRA_FLAGS=${FXT_EXTRA_FLAGS} RUNDEMO=true
        AA=$(grep 'BENCHARGS' $d | cut -d= -f2- | tr ' ' '@')
        for aa in ${=AA}; do  ## loop over benchmarks in one file
            a=$(echo $aa | tr '@' ' ' );
            echo "----- args=$a"
            eval time ${DEMOBIN} ${=a}
            echo -en '\n'
        done
        echo -en '\n\n'
    fi
done


exit 0;
#################################
