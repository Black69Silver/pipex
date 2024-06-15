NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc

#CFLAGS = -Wall -Wextra -Werror							# Uncomment before submitting. 
#CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address	# Do NOT use it with valgrind	# not working flags: ASAN_OPTIONS=detect_leaks=1 -fsanitize=leak -Wno-gnu-include-next -I ~/LeakSanitizer/include -L ~/LeakSanitizer -llsan
CFLAGS =  -Wall -Wextra -Werror -g						# Delete before submitting.

SOURCES = pipex.c pipex_execute.c \
			pipex_utils.c ft_split.c ft_memory_control.c

SOURCES_BONUS = pipex_bonus.c pipe_control_bonus.c pipex_execute_bonus.c \
				pipex_utils_bonus.c ft_split_bonus.c ft_memory_control_bonus.c

OBJECTS = $(SOURCES:.c=.o)

OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) $(OBJECTS_BONUS) -o $(NAME_BONUS)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re

test: fclean all bonus
# valgrind --trace-children=yes 												# produces many irrelevant errors
# --show-leak-kinds=all
#	valgrind --leak-check=full ./pipex infile "grep a1" "wc -w" outfile
#	valgrind --leak-check=full --track-fds=yes ./pipex infile "grep Hello" "wc -l" outfile
#	valgrind --leak-check=full ./pipex infile "grep Hello" "wc -l" outfile

#	./pipex infile "wc -w" "cat" outfile
#	< infile wc -w | cat >> outfile
#	"assets/deepthought.txt" "wc -w" "cat" "outs/test-xx.txt

#	./pipex infile "ls -l" "wc -l" outfile
#	../pipex "assets/deepthought.txt" "cat" "hostname" "outs/test-xx.txt"
#	./pipex "assets/deepthought.txt" "grep Now" "/bin/cat" "outs/test-xx.txt"

#	./pipex infile "fizzBuzz" "ls -l src/" outfile								# this should produce an error
#	./pipex infile "ls -l src/" "buzzFizz" outfile								# this should produce an error

#	./pipex infile "grep Hello" "awk \"'{count++} END {print count}'\"" outfile	# this should produce an error
#	< infile grep Hello | awk "'{count++} END {print count}'" >> outfile		# this should produce an error

#	./pipex infile "grep Hello" "awk '\"{count++} END {print count}\"'" outfile	# this should produce no error
#	< infile grep Hello | awk '"{count++} END {print count}"' >> outfile		# this should produce no error

# TestCase(3
#	./pipex infile 'sed    "s/And/But/"' 'grep But' outfile						# this should produce no error
#	< infile sed "s/And/But/" | grep But >> outfile								# this should produce no error

# TestCase(4
#	./pipex infile 'sed "s/And/But/"' "awk '{count++} END {print count}'" outfile	# this should produce no error
#	< infile sed "s/And/But/" | awk '{count++} END {print count}' >> outfile		# this should produce no error

# TestCase(5
#	./pipex infile 'sed "s/And/But/"' 'awk "{count++} END {print count}"' outfile	# this should produce no error
#	< infile sed "s/And/But/" | awk "{count++} END {print count}" >> outfile		# this should produce no error

# TestCase(6
#	./pipex infile 'sed "s/And/But/"' 'awk "{count++} END {printf \\"count: %i\\" , count}"' outfile	# this should produce no error, but is not working
#	< infile sed "s/And/But/" | awk "{count++} END {printf \"count: %i\" , count}" >> outfile			# this should produce no error

# TestCase(7
#	./pipex infile 'sed "s/And/But/"' "awk '{count++} END {printf \"count: %i\", count}'" outfile	# this should produce no error
#	< infile sed "s/And/But/" | awk '{count++} END {printf "count: %i", count}' >> outfile			# this should produce no error

# TestCase(8
#	./pipex infile "./script.sh" 'wc' outfile									# this should produce an error
#	< infile ./script.sh | wc >> outfile										# this should produce an error

#	./pipex_bonus infile "grep apple" "sort" "uniq" "wc" outfile				# bonus test
#	< infile grep apple | sort | uniq | wc >> outfile							# bonus test


#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile "grep Hello" "wc" outfile 
#	./pipex_bonus infile "grep Hello" "wc" outfile 
#	< infile grep Hello | wc >> outfile
#	@return:	number of lines with "Hello"; number of words and number of characters on these lines

#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile cat cat ls cat wc outfile								# bonus test
#	< infile cat | cat | ls | cat | wc >> outfile

#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile date "man env" cat "grep -i exit" outfile				# bonus test
#	< infile date | man env | cat | grep -i exit >> outfile																	# bonus test

#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile "ls -l src/" "grep .c" "wc -l" outfile					# bonus test, should produce an error
#	< infile ls -l src/ | grep .c | wc -l >> outfile																		# bonus test, should produce an error


#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile "tr -d !" "grep -v !" "sed 's/Hello/Salut/g'" outfile	# bonus test, but throws an error! Why?
#	< infile tr -d ! | grep -v ! | sed 's/Hello/Salut/g' >> outfile


#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile "grep Hello" "awk '{count++} END {print count}'" outfile		# this should produce no error
#	< infile grep Hello | awk '{count++} END {print count}' >> outfile																# this should produce no error

#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile "grep -v !" "sed 's/Hello/Salut/g'" "grep Salut" "wc -l" outfile	# bonus test
#	< infile tr -d ! | grep -v ! | sed 's/Hello/Salut/g' | grep Salut | wc -l >> outfile												# bonus test

#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile 'cat' 'grep And' "cat -e" 'wc' outfile					# bonus test
#	< infile cat | grep And | cat -e | wc >> outfile																		# bonus test

#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile "grep Hello" "not-executable" outfile					# this should produce an error, but not leaks
#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile "cat /dev/urandom" "head -1" outfile							# if running correctly, it will print one line of random characters, otherwise it will print infinite number of random characters
#	valgrind --leak-check=full --track-fds=yes ./pipex_bonus infile "sleep 3" "sleep 3" "sleep 3" "sleep 3" "sleep 3" outfile		# if not running correctly, it will wait for 6 seconds, otherwise 3 seconds
