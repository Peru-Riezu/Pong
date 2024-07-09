RED='\033[0;31m';
GREEN='\033[0;32m';
RESET='\033[0m';

cd .. && make > /dev/null;
cd api;
mkdir -p test_files

printf "PUT /create_account?name=7777777&password=44444444444444444444444444444444444444444444&nick_name=nick HTTP/1.1\r\n\r\n" > test_files/test1_input;
printf "api: successfully created account with:\n\tname: 7777777" > test_files/test1_expected_output;
printf "\n\tpassword: 44444444444444444444444444444444444444444444\n\tnick_name: nick\n" >> test_files/test1_expected_output;
printf "" > test_files/test1_expected_error_output;
./api < test_files/test1_input > test_files/test1_output 2> test_files/test1_error_output;
printf "test 1º:\n";
(cmp -s test_files/test1_output test_files/test1_expected_output && printf "\tstdout: ${GREEN}OK${RESET}\n") || printf "\tstdout: ${RED}KO${RESET}\n";
(cmp -s test_files/test1_error_output test_files/test1_expected_error_output && printf "\tstderr: ${GREEN}OK${RESET}\n") || printf "\tstderr: ${RED}KO${RESET}\n";

printf "PUT /create_account?name=7777777&password=44444444444444444444444444444444444444444444&nick_name=nick HTTP/1.1\r\n\r\n" > test_files/test2_input;
printf "" > test_files/test2_expected_output;
printf "api: error: user could not be created because a user whit that name already exists\n" > test_files/test2_expected_error_output;
./api < test_files/test2_input > test_files/test2_output 2> test_files/test2_error_output;
printf "test 2º:\n";
(cmp -s test_files/test2_output test_files/test2_expected_output && printf "\tstdout: ${GREEN}OK${RESET}\n") || printf "\tstdout: ${RED}KO${RESET}\n";
(cmp -s test_files/test2_error_output test_files/test2_expected_error_output && printf "\tstderr: ${GREEN}OK${RESET}\n") || printf "\tstderr: ${RED}KO${RESET}\n";

