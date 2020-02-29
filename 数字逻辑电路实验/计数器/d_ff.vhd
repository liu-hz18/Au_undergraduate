-- 异步复位D触发器 --
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity d_ff is
    port(
        clk: in std_logic;
        rst: in std_logic;
        pause: in std_logic;
        d: in std_logic;
        q: out std_logic;
        nq: out std_logic
    );
end d_ff;

architecture bhv of d_ff is
begin
    process(clk, rst)
    begin
        if rst = '1' then
            q <= '0';
            nq <= '1';
        elsif clk'event and clk='1' then
            if pause='0' then
                q <= d;
                nq <= not d;
            else --维持不变
                q <= not d;
                nq <= d;
            end if;
        end if;
    end process; 
end bhv;
