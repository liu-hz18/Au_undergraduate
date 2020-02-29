--逐次进位加法器，时延9ns左右--
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity fouradder is
    port(
        a, b: in std_logic_vector(3 downto 0);
        cin: in std_logic;
        s: out std_logic_vector(3 downto 0);
        cout: out std_logic
    );
end fouradder;

architecture bhv of fouradder is
    component fulladder
        port(
            ain, bin, ci: in std_logic;
            s, co: out std_logic
        );
    end component;
    signal c: std_logic_vector(3 downto 0);
begin
    u1: fulladder port map(ain=>a(0), bin=>b(0), ci=>cin , s=>s(0), co=>c(0) );
    u2: fulladder port map(ain=>a(1), bin=>b(1), ci=>c(0), s=>s(1), co=>c(1) );
    u3: fulladder port map(ain=>a(2), bin=>b(2), ci=>c(1), s=>s(2), co=>c(2) );
    u4: fulladder port map(ain=>a(3), bin=>b(3), ci=>c(2), s=>s(3), co=>cout );
end bhv;
