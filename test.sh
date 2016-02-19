#!/bin/zsh

echo 'ls -l'
echo 'ls -l' | ./minishell
read -n 1 -s

echo 'ls'
echo 'ls' | ./minishell
read -n 1 -s

echo '/bin/ls'
echo '/bin/ls' | ./minishell
read -n 1 -s

echo 'echo $HOME/$SHLVL/$HOME $SHLVL'
echo 'echo $HOME/$SHLVL/$HOME $SHLVL' | ./minishell
read -n 1 -s

echo 'cat auteur'
echo 'cat auteur' | ./minishell
read -n 1 -s

echo 'env'
echo 'env' | ./minishell
read -n 1 -s

echo 'setenv a b\nenv'
echo 'setenv a b\nenv' | ./minishell
read -n 1 -s

echo 'setenv a a\nenv'
echo 'setenv a a\nenv' | ./minishell
read -n 1 -s

echo 'unsetenv a\nenv'
echo 'unsetenv a\nenv' | ./minishell
read -n 1 -s

echo 'setenv b\nenv'
echo 'setenv b\nenv' | ./minishell
read -n 1 -s

echo 'env -u b\nenv'
echo 'env -u b\nenv' | ./minishell
read -n 1 -s

echo 'env -i ./minishell\nenv'
echo 'env -i ./minishell\nenv' | ./minishell
read -n 1 -s
