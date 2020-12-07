./1033_1_data_maker.exe

(./1033_1.exe <test.in) >test.out
(./1033_1_std.exe <test.in) >test_std.out

echo $(diff test.out test_std.out)
