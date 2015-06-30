#!/bin/bash

inputFile="XYModel.pro"
outputFile="tmp2.txt"

#Remove the output tmp file to ensure it doesn't already exist
# rm $outputFile

#For each line before the first header, copy over the line
foundHeader=false

while IFS='' read -r line || [[ -n $line ]]; do
	if [[ $line == HEADERS* ]] || $foundHeader;
	then
		foundHeader=true
	else
		echo "$line" >> $outputFile
	fi
	
done < "$inputFile"

#Store the indent prefix for later use
tabPrefix="            "

#Now add all the headers
prefix="HEADERS   = "
for filename in `find src -name '*.h'`; do
	echo "${prefix}${filename} \\" >> $outputFile
	if [ "${prefix}" != "${tabPrefix}" ];
	then
		prefix="${tabPrefix}"
	fi
done
echo "" >> $outputFile

#And all the source files
prefix="SOURCES   = "
for filename in `find src -name '*.cpp'`; do
	echo "${prefix}${filename} \\" >> $outputFile
	if [ "${prefix}" != "${tabPrefix}" ];
	then
		prefix="${tabPrefix}"
	fi
done
echo "" >> $outputFile

#And mv our output over the input file
mv $outputFile $inputFile
