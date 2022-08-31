# ./run_single.sh circ_file_name
# ./run_single.sh e1234567.circ
# ./run_single.sh some\ dir/another\ dir\ submission_file_/e1234567.circ

java -jar logisim.jar -grader grader-hw2.properties "$1" 2>&1 | tee eval.out

python3 tester.py

rm eval.out
