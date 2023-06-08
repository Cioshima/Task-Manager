
#include "pch.h"
#include "CppUnitTest.h"
//#include "../DevelopmentProject/DevelopmentProject.h"
#include "../DevelopmentProject/DevelopmentProject.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
        TEST_METHOD(AddTaskTest)
        {
            TaskManager taskManager;
            taskManager.addTask("Sleep", 12);
            taskManager.addTask("Sleep", 10);

        }

        TEST_METHOD(FindTaskTest)
        {
            TaskManager taskManager;
            
            taskManager.addTask("Eat", 2);
            taskManager.addTask("Shower", 1);

            taskManager.findTask("Eat");
            taskManager.findTask("Nothing");

        }

        TEST_METHOD(DisplayTaskTest)
        {
           
            TaskManager taskManager;
            
            taskManager.addTask("Work", 2);
            taskManager.addTask("Cook", 3);

            taskManager.displayTasks();
            taskManager.displayTasks();
        }

        TEST_METHOD(SortTaskTest)
        {
            TaskManager taskManager;
            
            taskManager.addTask("Clean", 1);
            taskManager.addTask("Brush Teeth", 1);
            taskManager.addTask("Pack", 10);

            taskManager.sortTasks();

        }

        TEST_METHOD(DeleteTaskTest)
        {
            TaskManager taskManager;
            
            taskManager.addTask("Run", 2);
            taskManager.addTask("Walk", 2);

            taskManager.deleteTask("Walk");
            
        }

	};
}
