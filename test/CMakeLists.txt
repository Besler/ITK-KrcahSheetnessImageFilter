add_executable(SheetnessUnitTest test_Sheetness.cxx)
target_link_libraries(SheetnessUnitTest gtest gtest_main)

add_test(ModifiedSheetnessUnitTests ModifiedSheetnessFunctorUnitTest)

add_executable(ModifiedSheetnessFunctorUnitTest test_ModifiedSheetnessFunctor.cxx)
target_link_libraries(ModifiedSheetnessFunctorUnitTest gtest gtest_main)

add_test(SheetnessUnitTests SheetnessUnitTest)