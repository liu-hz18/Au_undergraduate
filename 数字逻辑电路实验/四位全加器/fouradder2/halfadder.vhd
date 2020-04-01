--一位半加器--
library ieee;
use ieee.std_logic_1164.all;

entity halfadder is
    port(
        ain, bin: in std_logic;
        so, co: out std_logic
    );
end halfadder;

architecture bhv_half of halfadder is
begin
    co <= ain and bin;--for G_n
    so <= ain xor bin;--for P_n
end bhv_half;
