##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CoreLib
ConfigurationName      :=Debug
WorkspacePath          := "/home/valrandir/Desktop/Link to Core/Project/CodeLite"
ProjectPath            := "/mnt/hgfs/Core/Project/CodeLite/CoreLib"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Valrandir
Date                   :=12-12-02
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
Preprocessors          :=$(PreprocessorSwitch)CoreTargetLinux 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/mnt/hgfs/Core/Project/CodeLite/CoreLib/CoreLib.txt"
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
Objects=$(IntermediateDirectory)/Time_Time.Linux$(ObjectSuffix) $(IntermediateDirectory)/System_System.Unix$(ObjectSuffix) $(IntermediateDirectory)/Memory_Memory$(ObjectSuffix) 

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

$(IntermediateDirectory)/System_System.Unix$(ObjectSuffix): ../../../Source/CoreLib/System/System.Unix.cpp $(IntermediateDirectory)/System_System.Unix$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/hgfs/Core/Source/CoreLib/System/System.Unix.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/System_System.Unix$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/System_System.Unix$(DependSuffix): ../../../Source/CoreLib/System/System.Unix.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/System_System.Unix$(ObjectSuffix) -MF$(IntermediateDirectory)/System_System.Unix$(DependSuffix) -MM "/mnt/hgfs/Core/Source/CoreLib/System/System.Unix.cpp"

$(IntermediateDirectory)/System_System.Unix$(PreprocessSuffix): ../../../Source/CoreLib/System/System.Unix.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/System_System.Unix$(PreprocessSuffix) "/mnt/hgfs/Core/Source/CoreLib/System/System.Unix.cpp"

$(IntermediateDirectory)/Memory_Memory$(ObjectSuffix): ../../../Source/CoreLib/System/Memory/Memory.cpp $(IntermediateDirectory)/Memory_Memory$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/hgfs/Core/Source/CoreLib/System/Memory/Memory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Memory_Memory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Memory_Memory$(DependSuffix): ../../../Source/CoreLib/System/Memory/Memory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Memory_Memory$(ObjectSuffix) -MF$(IntermediateDirectory)/Memory_Memory$(DependSuffix) -MM "/mnt/hgfs/Core/Source/CoreLib/System/Memory/Memory.cpp"

$(IntermediateDirectory)/Memory_Memory$(PreprocessSuffix): ../../../Source/CoreLib/System/Memory/Memory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Memory_Memory$(PreprocessSuffix) "/mnt/hgfs/Core/Source/CoreLib/System/Memory/Memory.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Time_Time.Linux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Time_Time.Linux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Time_Time.Linux$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/System_System.Unix$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/System_System.Unix$(DependSuffix)
	$(RM) $(IntermediateDirectory)/System_System.Unix$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Memory_Memory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Memory_Memory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Memory_Memory$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/valrandir/Desktop/Link to Core/Project/CodeLite/.build-debug/CoreLib"


