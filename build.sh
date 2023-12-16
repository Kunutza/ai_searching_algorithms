directory=$(pwd)
name='puzzle_solve'
project_dir="$directory/test/"


#files="puzzle.c generator.c verify.c" 
files="main.c search/search.c arguments_validation/validate.c solution_writer/writer.c"
libs=''

gcc $files `$libs` -o $name -lm #&& "$project_dir" breadth 1 21 solution.txt
mv $name "${project_dir}"
