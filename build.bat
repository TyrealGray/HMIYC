@echo off
echo 建立日期 %date%
echo 建立日期 %date%>>E:\SkyHarpGames\buildLog.log
del E:\SkyHarpGames\HMIYC\CILog.txt
"%VS140COMNTOOLS%..\IDE\devenv.exe" "E:\SkyHarpGames\HMIYC\HuntMeIfYouCan\HuntMeIfYouCan.sln" /rebuild "Shipping|Win32" /out "E:\SkyHarpGames\HMIYC\CILog.txt""
type E:\SkyHarpGames\HMIYC\CILog.txt
type E:\SkyHarpGames\HMIYC\CILog.txt>>E:\SkyHarpGames\buildLog.log
echo 完成构建
echo 完成构建>>E:\SkyHarpGames\buildLog.log