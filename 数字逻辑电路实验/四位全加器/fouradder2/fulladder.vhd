
library ieee;
use ieee.std_logic_1164.all;

entity fulladder is
    port(
        a, b, ci: in std_logic;
        s: out std_logic;
        p, g: buffer std_logic
    );
end fulladder;

architecture bhv_full of fulladder is
begin
    p <= a xor b;
    g <= a and b;
    s <= ci xor p;
end bhv_full;
