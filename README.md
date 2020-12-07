# flipbook
Language to convert set of images to video/pdf.

# Dependecies
* opencv (python)
* fpdf (python)

# Primitives
* TList: Defined as-
```
TList <variable_name>
<file_name> <start_time> <end_time>
<file_name> <start_time> <end_time>
.
.
End
# <end_time> is not included
```
These are timed list, which says starting and ending time/page of a file

* UList: Defined as-
```
UList <variable_name>
<file_name>
<file_name>
.
.
End
```
These are untimed list, assumed to be one per frame.

* Folder: Defined as-
```
Folder <variable_name> <folder_path>
```
These are there to define any directory where the selected images are from.

* Frames: These are the basic block of video/pdf. A single frame is collection of images which can be overlapped together. Defined as-
```
Frames <variable_name>
UList list1
UList list2
.
.
.
end
```
Each *UList* represent single frame.

* Generating Video: Implemented as-
```
GenerateVideo <file_name> <Folder> <Frames>
```
*file_name* is output file name, Folder and Frames variable need to be passed.

* Generating PDF: Implemented as-
```
GeneratePDF <file_name> <Folder> <Frames>
```
*file_name* is output file name, Folder and Frames variable need to be passed.

Sample code is as:
```
UList images2
2020-11-26 (2).png
2020-11-26 (11).png
2020-11-26 (9).png
end

TList tlist
2020-11-26 (2).png 1 3
2020-11-26 (10).png 3 7
2020-11-26 (12).png 7 10
end

Folder folder ./imgs/

# create empty UList variable img
UList img
end

# create empty Frames variable f
Frames f
end

Position pos 1

# A basic loop
LoopBegin pos 10
AppendFrames f img
AppendUList img loop.jpg
LoopEnd

GenerateVideo out.avi folder f
```
* Compilation and Execution
```
Windows
$  g++ -std=c++11 .\utils\handlers.cpp .\utils\generator_functions.cpp -o parser.exe .\parser.cpp
$ ./parser test.flip
```

* Funcions:
```
AppendUList <UList> <file_name> : appends file_name to given UList
AppendTList <TList> <file_name> <start> <end> : appends file_name with interval to given TList
AppendFrames <Frames> <UList> : appends given UList to Frame
AccessUList <UList> <Position> : returns file_name at given position in given UList
UList2Frames <UList> <Frames> : convert given UList to Frames
TList2UList <TList> <UList> : converts TList to UList
```
If we define Position FPS (FPS can be seen as reserved keyword for FPS in video) before calling this function, if FPS is negative then it will write frame wise other wise it will write time-wise. Example:
```
Position FPS 3
TList tlist
a1.png 1 2
a2.png 2 3
end

TList2UList tlist ulist
```
FPS is 3, so for given time 1-2, each second need 3 frames. Entries of ulist will be:
```
a1.png
a1.png
a1.png
a2.png
a2.png
a2.png
```
For negative FPS, we are writing each frame, but with |FPS| frames per second:
```
Position FPS -3
TList tlist
a1.png 1 3
a2.png 3 5
end

TList2UList tlist ulist
```
Entries of ulist will be:
```
a1.png
a2.png
```
* Loops (very basic ones)
```
# this is an empty UList
UList ulist
end

#create a position variable
Position pos 0

# LoopBegin <Position> <number>
# loops while pos < <number>
LoopBegin pos 10
AppendUList ulist image1.png
LoopEnd

# Will return with ulist having 10 image1.png
```
Loops can be useful here:
```
Position FPS 8
TList tlist
image1.png 1 3
image2.png 3 6
End

# This will give a ulist of lenght 40
TList2UList tlist ulist1

UList ulist2
end

Position pos 0
LoopBegin pos 40
AppendUList ulist2 $ AccessUList ulist1 pos
LoopEnd

# will copy ulist1 to ulist2
```
$ just means that the control from now on will be trandered to AccessUList.

Basic tokenisation is built, hence space between each different token is required.

* Future Scopes
1. Implementing Advanced Tokenisation.
2. Layered Frames: Frames are List of Lists, each list for a frame to show. Layering of images can be implemented.