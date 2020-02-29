--一位半加器--
library ieee;
use ieee.std_logic_1164.all;

entity halfadder is
    port(
        a, b: in std_logic;
        so, co: out std_logic
    );
end halfadder;

architecture bhv_half of halfadder is
begin
    co <= a and b;
    so <= a xor b;
end bhv_half;
