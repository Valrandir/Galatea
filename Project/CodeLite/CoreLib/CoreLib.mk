##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CoreLib
ConfigurationName      :=Debug
WorkspacePath          := "/home/dlaplante/Desktop/Core/Project/CodeLite"
ProjectPath            := "/mnt/hgfs/Core/Project/CodeLite/CoreLib"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=dlaplante
Date                   :=12-12-03
CodeLitePath           :="/home/dlaplante/.codelite"
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
Objects=$(IntermediateDirectory)/Time_Time.Linux$(ObjectSuffix) $(IntermediateDirectory)/System_System.Linux$(ObjectSuffix) $(IntermediateDirectory)/Memory_Memory$(ObjectSuffix) $(IntermediateDirectory)/Threading_Thread.Linux$(ObjectSuffix) 

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
	@$(MakeDirCommand) "/home/dlaplante/Desktop/Core/Project/CodeLite/.build-debug"
	@echo rebuilt > "/home/dlaplante/Desktop/Core/Project/CodeLite/.build-debug/CoreLib"

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

$(IntermediateDirectory)/System_System.Linux$(ObjectSuffix): ../../../Source/CoreLib/System/System.Linux.cpp $(IntermediateDirectory)/System_System.Linux$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/hgfs/Core/Source/CoreLib/System/System.Linux.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/System_System.Linux$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/System_System.Linux$(DependSuffix): ../../../Source/CoreLib/System/System.Linux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/System_System.Linux$(ObjectSuffix) -MF$(IntermediateDirectory)/System_System.Linux$(DependSuffix) -MM "/mnt/hgfs/Core/Source/CoreLib/System/System.Linux.cpp"

$(IntermediateDirectory)/System_System.Linux$(PreprocessSuffix): ../../../Source/CoreLib/System/System.Linux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/System_System.Linux$(PreprocessSuffix) "/mnt/hgfs/Core/Source/CoreLib/System/System.Linux.cpp"

$(IntermediateDirectory)/Memory_Memory$(ObjectSuffix): ../../../Source/CoreLib/System/Memory/Memory.cpp $(IntermediateDirectory)/Memory_Memory$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/hgfs/Core/Source/CoreLib/System/Memory/Memory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Memory_Memory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Memory_Memory$(DependSuffix): ../../../Source/CoreLib/System/Memory/Memory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Memory_Memory$(ObjectSuffix) -MF$(IntermediateDirectory)/Memory_Memory$(DependSuffix) -MM "/mnt/hgfs/Core/Source/CoreLib/System/Memory/Memory.cpp"

$(IntermediateDirectory)/Memory_Memory$(PreprocessSuffix): ../../../Source/CoreLib/System/Memory/Memory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Memory_Memory$(PreprocessSuffix) "/mnt/hgfs/Core/Source/CoreLib/System/Memory/Memory.cpp"

$(IntermediateDirectory)/Threading_Thread.Linux$(ObjectSuffix): ../../../Source/CoreLib/System/Threading/Thread.Linux.cpp $(IntermediateDirectory)/Threading_Thread.Linux$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/hgfs/Core/Source/CoreLib/System/Threading/Thread.Linux.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Threading_Thread.Linux$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Threading_Thread.Linux$(DependSuffix): ../../../Source/CoreLib/System/Threading/Thread.Linux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Threading_Thread.Linux$(ObjectSuffix) -MF$(IntermediateDirectory)/Threading_Thread.Linux$(DependSuffix) -MM "/mnt/hgfs/Core/Source/CoreLib/System/Threading/Thread.Linux.cpp"

$(IntermediateDirectory)/Threading_Thread.Linux$(PreprocessSuffix): ../../../Source/CoreLib/System/Threading/Thread.Linux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Threading_Thread.Linux$(PreprocessSuffix) "/mnt/hgfs/Core/Source/CoreLib/System/Threading/Thread.Linux.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Time_Time.Linux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Time_Time.Linux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Time_Time.Linux$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/System_System.Linux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/System_System.Linux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/System_System.Linux$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Memory_Memory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Memory_Memory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Memory_Memory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Threading_Thread.Linux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Threading_Thread.Linux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Threading_Thread.Linux$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/dlaplante/Desktop/Core/Project/CodeLite/.build-debug/CoreLib"


