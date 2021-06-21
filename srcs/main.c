#include "../includes/pipex.h"

int reset_comand(t_command *command, char **env)
{
    int i;
    char *str;

    ft_bzero(command, sizeof(t_command));
    while (env[i] != 0)
    {
        str = ft_strnstr(env[i], "PATH=", 5);
        if (str)
        {
            command->evd = str;
            return (1);
        }
    }
    return (0);
}

int main(int argc, char **argv, char **env)
{
    t_command command;
    int i;

    printf("el número de argumentos es: %d\n", argc);
    if (argc < 5)
    {        
        show_error("Wrong arguments", 0);
    }
    i = 1;
    while (i < argc)
    {
        reset_comand(&command, env);
        command.evd = env;
        if (i == 1)
        {
            printf("se va a ejecutar la cabecera\n");
            command.is_firts = 1;
            load_command(&command, argv[i], argv[i + 1]);
            i += 2;
        }
        else if (i == argc - 2)
        {
             printf("para i: %d se va a ejecutar el final con\n", i);
            load_command(&command, argv[i], argv[i + 1]);
            i += 2;
            
        }
        else
        {
           printf("se va a ejecutar un intermedio para i: %d\n", i);
            load_command(&command, 0, argv[i++]);
        }
        exec_command(&command);
    }
}