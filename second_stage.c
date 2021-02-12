#include "second_stage.h"
#include "constants.h"
#include "text_process.h"
#include "data_structures.h"
#include "assembler_main.h"


int second_stage(FILE *file){
    char line[MAX_LINE];
    char argument[MAX_ARGUMENT];
    char label[MAX_LABEL];
    int directive_type = data;
    int ic_pointer, i;
    enum boolean IS_LABEL = FALSE, IS_DIRECT = FALSE, CONTINUE = FALSE;

    printf("SECOND STAGE STARTED\n");
    ic_pointer = 100;
    while (!feof(file))
    {
        get_line(file, line);
        printf("[ ] - current line: %s\n", line);

        if (!is_comment_line(line) && !is_empty_line(line)){
            get_first_token(line, argument);
            if (get_label(line, label)==1){
                IS_LABEL = TRUE;
                get_next_token(argument);
                if ((directive_type = is_directive(argument)) != -1){
                    IS_DIRECT = TRUE;
                }
            }
            else if ((directive_type = is_directive(argument)) != -1){
                IS_DIRECT = TRUE;
            }
        }

        if ( directive_type == entry){
            get_next_token(argument);
            /* search the label in the symbol list */
            if(add_entry_to_symbol(argument)==0){
                /* print error */
            }
        }
        else if (directive_type == data || directive_type == string || directive_type == external)
        {
            CONTINUE = TRUE;
        }

        if(CONTINUE == FALSE){
            
        }

        /* AMIT - 6 */
        if ((i = get_source(command_memory[ic_pointer].w)) == 1 || i == 2){
            
        }
        if ((i = get_dest(command_memory[ic_pointer].w)) == 1 || i == 2){
            
        }

        
        
        
    }
    print_table_symbol(root);
    return 1;
}
