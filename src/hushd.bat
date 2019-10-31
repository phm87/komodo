@call :GET_CURRENT_DIR
@cd %THIS_DIR%
komodod.exe -ac_name=HUSH3 -ac_sapling=1 -ac_reward=0,1125000000,562500000 -ac_halving=129,340000,840000 -ac_end=128,340000,5422111 -ac_eras=3 -ac_blocktime=150 -ac_cc=2 -ac_ccenable=228,234,235,236,241 -ac_founders=1 -ac_supply=6178674 -ac_perc=11111111 -clientname=GoldenSandtrout -addnode=64.120.113.130 -addnode=209.58.144.205 -addnode=94.130.35.94 -addnode=188.165.212.101 -ac_cclib=hush3 -ac_script=76a9145eb10cf64f2bab1b457f1f25e658526155928fac88ac -daemon %1 %2 %3 %4 %5 %6 %7 %8 %9
@goto :EOF

:GET_CURRENT_DIR
@pushd %~dp0
@set THIS_DIR=%CD%
@popd
@goto :EOF
