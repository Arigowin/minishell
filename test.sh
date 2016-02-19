#!/bin/zsh

echo 'echo ls -l'
echo 'ls -l' | ./minishell
read -n 1 -s

echo 'echo ls'
echo 'ls' | ./minishell
read -n 1 -s

echo 'echo /bin/ls'
echo '/bin/ls' | ./minishell
read -n 1 -s

echo 'echo echo $HOME/$SHLVL/$HOME $SHLVL'
echo 'echo $HOME/$SHLVL/$HOME $SHLVL' | ./minishell
read -n 1 -s

echo 'echo echo $z'
echo 'echo $z' | ./minishell
read -n 1 -s

echo 'echo cat auteur'
echo 'cat auteur' | ./minishell
read -n 1 -s

echo 'echo env'
echo 'env' | ./minishell
read -n 1 -s

echo 'echo setenv a b\necho env'
echo 'setenv a b\nenv' | ./minishell
read -n 1 -s

echo 'echo setenv a a\necho env'
echo 'setenv a a\nenv' | ./minishell
read -n 1 -s

echo 'echo unsetenv a\necho env'
echo 'unsetenv a\nenv' | ./minishell
read -n 1 -s

echo 'echo setenv b\necho env'
echo 'setenv b\nenv' | ./minishell
read -n 1 -s

echo 'echo env -u b\necho env'
echo 'env -u b\nenv' | ./minishell
read -n 1 -s

echo 'echo env -i ./minishell'
echo 'env -i ./minishell' | ./minishell
read -n 1 -s

echo 'echo exit'
echo 'exit' | ./minishell
