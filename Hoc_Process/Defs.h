/*
* This is a definition file that supposed to define a common language for the project.
*/

#define NOT_FOUND 0
#define EQUALS 0
#define ZERO 0
#define FIRST 0
#define START 1
#define ONE 1
#define SECOND 1

#define COMMENT_S "#" // for string
#define COMMENT_C '#' // for char
#define Y_SPACE " "
#define EMPTY ""

#define SUFFIX_MOD ".mod" 
#define Y_SUFFIX "SUFFIX"
#define COPY_SUFFIX ".copy"
#define STR_OR " or "



/***************************** Errors *****************************/

// Error: File Open
#define ERR_FO "Error: could not open the file: "
#define ERR_DIR "Error: could not open the directory "
#define ERR_FILE "Encountered an error in the file: "
#define ERR_MIS "Error: the file is missing the line: "
#define ERR_DEL "Error: the file couldn't get deleted correctly: "

/***************************** Files *****************************/
// Output Files
#define GLB "output//64GLOBAL.csv"
#define MDL64 "output//64MDL.csv"
#define PP64 "output//64PP.csv"
#define T64 "output//64T.csv"

// Resources Files

// (Relative pathes).
#define DEFAULT_HOC_FILE "resources/example.hoc" 
#define DEFAULT_HOC_COMMANDS_FILE "resources/hoc_command_insert.txt"

#define BRANCHING "branching.mod"

#define HOC "hoc"
#define TXT "txt"


/***************************** Tokens *****************************/
#define TKN_PATH "Insert_Path"
#define TKN_HOC_INSRT "//ADD STUFF HERE"

/***************************** Paths *****************************/

/************************** IMPORTANT **************************** !!!!!!!!!!!!!!!!!!!!!!!!
* This path should be modified when changing computers.
* TODO - get this path in the constructor.
*/
#define DEFULT_DIR_PATH "d:/Users/Yanai/Desktop/Compiler_Project/Neuron_GPU/Hoc_Process"



