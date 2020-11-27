# flipbook
Language to convert set of images to video/pdf (HASURA Tech Task)

# Dependecies
* opencv (python)
* fpdf (python)

# Primitives
* TList: Defined as-
TList <variable_name>
<file_name> <start_time> <end_time>
<file_name> <start_time> <end_time>
.
.
End

These are timed list, which says starting and ending time/page of a file

* UList: Defined as-
UList <variable_name>
<file_name>
<file_name>
.
.
End

These are untimed list, assumed to be one per frame.

* Folder: Defined as-
Folder <variable_name> <folder_path>
These are there to define any directory where the selected images are from.

* Frames: These are the basic block of video/pdf. A single frame is collection of images which can be overlapped together. Defined as-
Frames <variable_name>
UList list1
UList list2
.
.
.
end

Each UList represent single frame.

* Generating Video: Implemented as-
GenerateVideo <file_name> <Folder> <Frames>
file_name is output file name, Folder and Frames variable need to be passed.

* Generating PDF: Implemented as-
GeneratePDF <file_name> <Folder> <Frames>
file_name is output file name, Folder and Frames variable need to be passed.