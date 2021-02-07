#include "second_stage.h"
#include "constants.h"
#include "text_process.h"


int second_stage(FILE *file){
    char line[MAX_LINE];
    char argument[MAX_ARGUMENT];
    char label[MAX_LABEL];
    int directive_type = data;
    enum boolean IS_LABEL = FALSE, IS_DIRECT = FALSE;

    while (!feof(file))
    {
        get_line(file, line);

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

        if (directive_type == data || directive_type == string || directive_type == external)
        {
            continue;
        }
        
    }
    return 1;
}
