#!/bin/bash

echo "\t************************************************"
echo '\t\t\tls -l'
echo "\t************************************************"
echo 'ls -l' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tls'
echo "\t************************************************"
echo 'ls' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\t/bin/ls'
echo "\t************************************************"
echo '/bin/ls' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tls ~+ ~- ~\nenv'
echo "\t************************************************"
echo 'ls ~+ ~- ~' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\techo $HOME/$SHLVL/$HOME $SHLVL'
echo "\t************************************************"
echo 'echo $HOME/$SHLVL/$HOME $SHLVL' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\techo $z'
echo "\t************************************************"
echo 'echo $z' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tcat auteur'
echo "\t************************************************"
echo 'cat auteur' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tenv'
echo "\t************************************************"
echo 'env' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tsetenv a b\n\t\t\techo env'
echo "\t************************************************"
echo 'setenv a b\nenv' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tsetenv a a\n\t\t\techo env'
echo "\t************************************************"
echo 'setenv a a\nenv' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tunsetenv a\n\t\t\techo env'
echo "\t************************************************"
echo 'unsetenv a\nenv' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tsetenv b\n\t\t\techo env'
echo "\t************************************************"
echo 'setenv b\nenv' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tenv -u b\n\t\t\techo env'
echo "\t************************************************"
echo 'env -u b\nenv' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tsetenv'
echo "\t************************************************"
echo 'setenv' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tenv -i ./minishell'
echo "\t************************************************"
echo 'env -i ./minishell' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tcd'
echo "\t************************************************"
echo 'cd\nls' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tsetenv OLDPWD /\n\t\t\tcd -\n\t\t\tcd -'
echo "\t************************************************"
echo 'setenv OLDPWD /\ncd -\nls\ncd -\nls' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tcd ~'
echo "\t************************************************"
echo 'cd ~\nls' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\tcd libft'
echo "\t************************************************"
echo 'cd libft\nls' | ./minishell
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\texit'
echo "\t************************************************"
echo 'exit' | ./minishell
echo $?
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\texit a'
echo "\t************************************************"
echo 'exit a' | ./minishell
echo $?
echo "\t************************************************"
read -n 1 -s

echo "\t************************************************"
echo '\t\t\texit 10'
echo "\t************************************************"
echo 'exit 10' | ./minishell
echo $?
echo "\t************************************************"

# test a faire a la main
# echo 'setenv b=b'
# echo 'echo setenv b=b\nenv' | ./minishell
# read -n 1 -s
