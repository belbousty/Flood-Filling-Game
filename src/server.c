#include <stdlib.h>

#include <stdio.h>

#include <dlfcn.h>

#include <ctype.h>

#include <unistd.h>

#include <getopt.h>

#include "spread.h"


int main(int argc, char * argv[]) {

    int opt;
    int length = 4;
    enum graph_type_t graph_type = DONUT;
    int nb_color = MAX_COLOR;
    int nb_forbidden_color = 1;
    enum color_type_t color_type = ALEATOIRE;
    while ((opt = getopt(argc, argv, "m:t:c:a:f:")) != -1) {
        switch (opt) {
        case 'm':
            length = atoi(optarg);
            break;
        case 't':
            if ( * optarg == 'c') {
                graph_type = SQUARE;
            } else if ( * optarg == 'd') {
                graph_type = DONUT;
            } else if ( * optarg == 'h') {
                graph_type = HGRAPH;
            } else if ( * optarg == 't') {
                graph_type = TORUS;
            }
            break;
        case 'c':
            nb_color = atoi(optarg);
            break;
        case 'a':
            if ( * optarg == 'a') {
                color_type = ALEATOIRE;
            } else if ( * optarg == 'c') {
                color_type = CYCLIQUE;
            } else if ( * optarg == 'p') {
                color_type = PONT;
            } else if ( * optarg == 's') {
                color_type = SYMETRIQUE;
            }
            break;
        case 'f':
            nb_forbidden_color = atoi(optarg);
            break;
        default:
            printf("Arguments incorrects\n");
            printf("%s [-m length] [-t graph_type] [-c nbre of colors] [-a color_type] [-f nombre of forbidden player]\n", argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }
    char * error;
    void * handle[NUM_PLAYERS] = {
        dlopen("install/libplayer4.so", RTLD_LAZY),
        dlopen("install/libplayer5.so", RTLD_LAZY)
    };
    int args = argc - 1;
    if (argv[args][0] == '.' && argv[args][1] == '/') {
        handle[1] = dlopen(argv[args], RTLD_LAZY);
        if (argv[args - 1][0] == '.' && argv[args - 1][1] == '/') {
            handle[0] = dlopen(argv[args - 1], RTLD_LAZY);
        }
    }
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (!handle[i]) {
            fputs(dlerror(), stderr);
            exit(1);
        }
    }

    struct graph_t * main_graph = graph_init(length * length, graph_type);
    struct graph_t * Copy_graph1 = graph_init(length * length, graph_type);
    struct graph_t * Copy_graph2 = graph_init(length * length, graph_type);
    graph_compressed_init(main_graph);
    graph_compressed_init(Copy_graph1);
    graph_compressed_init(Copy_graph2);
    struct graph_t * Copy_graph[NUM_PLAYERS] = {
        Copy_graph1,
        Copy_graph2
    };
    enum color_t * main_colors = colors_init(main_graph, color_type, nb_color);
    enum color_t * Copy_colors1 = colors_init(Copy_graph1, color_type, nb_color);
    enum color_t * Copy_colors2 = colors_init(Copy_graph2, color_type, nb_color);
    enum color_t * Copy_colors[NUM_PLAYERS] = {
        Copy_colors1,
        Copy_colors2
    };
    struct color_set_t forbidden[2] = {
        {
            .t = {
                '-',
                '-',
                '-',
                '-',
                '-',
                '-',
                '-',
                '-'
            }
        },
        {
            .t = {
                '-',
                '-',
                '-',
                '-',
                '-',
                '-',
                '-',
                '-'
            }
        }
    };
    void( * initialize)();

    for (int i = 0; i < NUM_PLAYERS; i++) {
        initialize = dlsym(handle[i], "initialize");
        initialize(i, Copy_graph[i], Copy_colors[i], forbidden);
    }

    struct color_set_t dyn_forbidden[NUM_PLAYERS];
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < MAX_COLOR; j++) {
            dyn_forbidden[i].t[j] = '-';
        }
    }

    struct move_t move = {
        .c = NO_COLOR
    };
    int indexe = 1;
    int bool = 1;
    print_color(main_colors, length * length);
    printf("\n");
    struct move_t( * play)();
    int count = 0;
    while (bool && count < 2 ) {
        count = 0;
        for (int i = 0; i < NUM_PLAYERS; i++) {
            play = dlsym(handle[i], "play");
            move = play(move);
            printf("\n the move is %d \n", move.c);

            update__forbidden(main_graph, main_colors, i, dyn_forbidden);
            //update__forbidden(main_graph,main_colors,(i==1)?0:1,dyn_forbidden);
            bool = spread__colors(main_graph, move, i, forbidden, dyn_forbidden, main_colors);
            if (bool == 0)
                break;
            printf("bool :%d \n", bool);
            print_color(main_colors, length * length);
            if (move.c == NO_COLOR) {
                count++;
            }
        }
    }

    char
    const * ( * player_name1)() = dlsym(handle[0], "get_player_name");
    char
    const * ( * player_name2)() = dlsym(handle[1], "get_player_name");
    printf("SCORE %s :\n%d\n", player_name1(), score__of_player(main_graph, main_colors, 0));
    printf("SCORE %s :\n%d\n", player_name2(), score__of_player(main_graph, main_colors, 1));
    if (score__of_player(main_graph, main_colors, 0) > score__of_player(main_graph, main_colors, 1)) {
        printf("The winner is : %s\n", player_name1());
    } else if (score__of_player(main_graph, main_colors, 0) < score__of_player(main_graph, main_colors, 1)) {
        printf("The winner is : %s\n", player_name2());
    } else {
        printf("Draw\n");
    }

    void( * finalize)();
    for (int i = 0; i < NUM_PLAYERS; i++) {
        finalize = dlsym(handle[i], "finalize");
        finalize();
    }

    free_graph(main_graph);
    free_colors(main_colors);

    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }
    for (int i = 0; i < NUM_PLAYERS; i++) {
        dlclose(handle[i]);
    }
    return 0;
}
