--Look Ahead Carry four-bit Adder, Time loss: 9ns--
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
            a, b, ci: in std_logic;
            p, g, s: out std_logic
        );
    end component;
    signal p, g, c: std_logic_vector(3 downto 0);
    
begin
    u0: fulladder port map(a=>a(0), b=>b(0), ci=>cin, p=>p(0), g=>g(0), s=>s(0));
    u1: for i in 1 to 3 generate
        ux: fulladder port map(a=>a(i), b=>b(i), ci=>c(i-1), p=>p(i), g=>g(i), s=>s(i));
    end generate;
    c(0) <= g(0) or (p(0) and cin);
    c(1) <= g(1) or (p(1) and g(0)) or (p(1) and p(0) and cin);
    c(2) <= g(2) or (p(2) and g(1)) or (p(2) and p(1) and g(0)) 
                 or (p(2) and p(1) and p(0) and cin);
    c(3) <= g(3) or (p(3) and g(2)) or (p(3) and p(2) and g(1)) 
                 or (p(3) and p(2) and p(1) and g(0)) 
                 or (p(3) and p(2) and p(1) and p(0) and cin);
    cout <= c(3);
end bhv;