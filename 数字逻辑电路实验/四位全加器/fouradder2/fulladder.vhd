--一位全加器--
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
    component halfadder
        port(
            ain, bin: in std_logic;
            so, co: out std_logic
        );
    end component;
begin
    u1: halfadder port map(ain=>a, bin=>b, so=>p, co=>g);
    s <= ci xor p;
end bhv_full;
