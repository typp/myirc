##
## Makefile for  in /home/sin/rendu/PSU_tek2/PSU_2014_myirc
##
## Made by SiN
## Login   <sin@epitech.net>
##
## Started on  Mon Mar 23 12:24:19 2015 
## Last update Thu Apr 09 10:14:32 2015 Cyril La Valle
##

all:		client server

client:
		make -C ./cli

server:
		make -C ./serv

clean:
		make clean -C ./serv
		make clean -C ./cli

fclean:		clean
		make fclean -C ./serv
		make fclean -C ./cli

re:		fclean all
