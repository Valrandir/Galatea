##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CoreLib
ConfigurationName      :=Debug
WorkspacePath          := "/home/valrandir/Desktop/Link to Core/Project/CodeLite"
ProjectPath            := "/home/valrandir/Desktop/Link to Core/Project/CodeLite/CoreLib"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Valrandir
Date                   :=12-11-29
CodeLitePath           :="/home/valrandir/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../../../Build/Linux/$(ProjectName).lib
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/valrandir/Desktop/Link to Core/Project/CodeLite/CoreLib/CoreLib.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/Time_Time.Linux$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/valrandir/Desktop/Link to Core/Project/CodeLite/.build-debug"
	@echo rebuilt > "/home/valrandir/Desktop/Link to Core/Project/CodeLite/.build-debug/CoreLib"

./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Time_Time.Linux$(ObjectSuffix): ../../../Source/CoreLib/System/Time/Time.Linux.cpp $(IntermediateDirectory)/Time_Time.Linux$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/hgfs/Core/Source/CoreLib/System/Time/Time.Linux.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Time_Time.Linux$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Time_Time.Linux$(DependSuffix): ../../../Source/CoreLib/System/Time/Time.Linux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Time_Time.Linux$(ObjectSuffix) -MF$(IntermediateDirectory)/Time_Time.Linux$(DependSuffix) -MM "/mnt/hgfs/Core/Source/CoreLib/System/Time/Time.Linux.cpp"

$(IntermediateDirectory)/Time_Time.Linux$(PreprocessSuffix): ../../../Source/CoreLib/System/Time/Time.Linux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Time_Time.Linux$(PreprocessSuffix) "/mnt/hgfs/Core/Source/CoreLib/System/Time/Time.Linux.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Time_Time.Linux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Time_Time.Linux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Time_Time.Linux$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/valrandir/Desktop/Link to Core/Project/CodeLite/.build-debug/CoreLib"


