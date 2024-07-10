RED='\033[0;31m';
GREEN='\033[0;32m';
RESET='\033[0m';

cd .. && make > /dev/null;
cd api;
mkdir -p test_files

#test 1º
########################################################################################################
#test 1º input
printf "PUT /create_account?" > test_files/test1_input;
printf "name=7777777" >> test_files/test1_input;
printf "&password=44444444444444444444444444444444444444444444" >> test_files/test1_input;
printf "&nick_name=nick" >> test_files/test1_input;
printf " HTTP/1.1\r\n\r\n" >> test_files/test1_input;

#tets 1º expected normal output
printf "api: successfully created account with:\n" > test_files/test1_expected_output;
printf "\tname: 7777777\n" >> test_files/test1_expected_output;
printf "\tpassword: 44444444444444444444444444444444444444444444\n" >> test_files/test1_expected_output;
printf "\tnick_name: nick\n" >> test_files/test1_expected_output;

#tets 1º expected error output
printf "" > test_files/test1_expected_error_output;

#execute command and get results
./api < test_files/test1_input > test_files/test1_output 2> test_files/test1_error_output;

#test one print result
printf "test 1º:\n";

if (cmp -s test_files/test1_output test_files/test1_expected_output)
then
	printf "\tstdout: ${GREEN}OK${RESET}\n"
else
	printf "\tstdout: ${RED}KO${RESET}\n";
fi

if (cmp -s test_files/test1_error_output test_files/test1_expected_error_output)
then
	printf "\tstderr: ${GREEN}OK${RESET}\n"
else
	printf "\tstderr: ${RED}KO${RESET}\n";
fi
########################################################################################################


#test 2º
########################################################################################################
#test 2º input
printf "PUT /create_account?" > test_files/test2_input;
printf "name=7777777" >> test_files/test2_input;
printf "&password=44444444444444444444444444444444444444444444" >> test_files/test2_input;
printf "&nick_name=nick" >> test_files/test2_input;
printf " HTTP/1.1\r\n\r\n" >> test_files/test2_input;

#tets 2º expected normal output
printf "" > test_files/test2_expected_output;

#tets 2º expected error output
printf "api: error: user could not be created because a user whit that name already exists\n" > test_files/test2_expected_error_output;

#execute command and get results
./api < test_files/test2_input > test_files/test2_output 2> test_files/test2_error_output;

#test one print result
printf "test 2º:\n";

if (cmp -s test_files/test2_output test_files/test2_expected_output)
then
	printf "\tstdout: ${GREEN}OK${RESET}\n"
else
	printf "\tstdout: ${RED}KO${RESET}\n";
fi

if (cmp -s test_files/test2_error_output test_files/test2_expected_error_output)
then
	printf "\tstderr: ${GREEN}OK${RESET}\n"
else
	printf "\tstderr: ${RED}KO${RESET}\n";
fi
########################################################################################################
