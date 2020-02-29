--一位全加器--
library ieee;
use ieee.std_logic_1164.all;

entity fulladder is
    port(
        ain, bin, ci: in std_logic;
        s, co: out std_logic
    );
end fulladder;

architecture bhv_full of fulladder is
    component halfadder
        port(
            a, b: in std_logic;
            so, co: out std_logic
        );
    end component;
    signal s1, c1, c2: std_logic;
begin
    u1: halfadder port map(a=>ain, b=>bin, so=>s1, co=>c1);
    u2: halfadder port map(a=>s1, b=>ci, so=>s, co=>c2);
    co <= c1 or c2;
end bhv_full;