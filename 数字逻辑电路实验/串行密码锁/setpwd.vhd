
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity setpwd is
    port(
        clk, rst: in std_logic;
        mode: in std_logic_vector(1 downto 0);
        code: in std_logic_vector(3 downto 0);
        pwd0, pwd1, pwd2, pwd3: out std_logic_vector(3 downto 0);
        currentnum: out std_logic_vector(6 downto 0)
    );
end setpwd;

architecture bhv of setpwd is
    component decoder
    port(
        bit_4_vec: in std_logic_vector(3 downto 0);
        bit_7_vec: out std_logic_vector(6 downto 0)
    );
    end component;
    signal state: integer := 0;
begin
    u0: decoder port map(bit_4_vec=>code, bit_7_vec=>currentnum);--显示当前输入数字
    process(clk, rst)
    begin
        if rst = '1' then --异步复位(同步复位直接放在下面的if下就可以)
            state <= 1;
        elsif clk'event and clk = '1' then
            if mode = "00" then
                case state is
                when 1 =>
                    pwd0 <= code;
                    state <= 2;
                when 2 =>
                    pwd1 <= code;
                    state <= 3;
                when 3 =>
                    pwd2 <= code;
                    state <= 4;
                when 4 =>
                    pwd3 <= code;
                    state <= 0;
                when others => null;
                end case;
            end if;
        end if;
    end process;
end bhv;
