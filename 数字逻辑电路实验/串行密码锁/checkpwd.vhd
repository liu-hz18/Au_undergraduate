-- 验证密码:使用状态机 --
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity checkpwd is
    port(
        clk, rst: in std_logic;
        mode: in std_logic_vector(1 downto 0);
        code: in std_logic_vector(3 downto 0);
        unlock, error, alarm: buffer std_logic;
        pwd0, pwd1, pwd2, pwd3: in std_logic_vector(3 downto 0);--4位16进制密码，由setpwd提供
        currentnum: out std_logic_vector(6 downto 0) -- 数码管输出当前数位
    );
    type fourbitpwd is array(3 downto 0) of integer; 
end checkpwd;

architecture bhv of checkpwd is
    component decoder
    port(
        bit_4_vec: in std_logic_vector(3 downto 0);
        bit_7_vec: out std_logic_vector(6 downto 0)
    );
    end component;
    signal state: integer := 0; --状态机当前状态
    signal cnt: integer := 0;--输入错误的次数
    constant adminpwd: fourbitpwd := (0, 0, 0, 0);--admin密码设为0000
begin
    u0: decoder port map(bit_4_vec=>code, bit_7_vec=>currentnum);
    process(clk, rst)
    begin
        if rst = '1' then --reset时alarm不清零
            state <= 1;--状态机:i状态开始接受第i位密码
            unlock <= '0';
            error <= '0';
            if alarm = '1' then
                cnt <= 0;
            end if;
        elsif clk'event and clk='1' then
            if mode = "01" then --user-输入密码模式
                case state is
                when 1 =>
                    if code = pwd0 then
                        state <= 2;
                    else
                        error <= '1';--输入错误
                        cnt <= cnt + 1;
                        state <= 0;
                    end if;
                when 2 =>
                    if code = pwd1 then
                        state <= 3;
                    else
                        error <= '1';
                        cnt <= cnt + 1;
                        state <= 0;
                    end if;
                when 3 =>
                    if code = pwd2 then
                        state <= 4;
                    else 
                        error <= '1';
                        cnt <= cnt + 1;
                        state <= 0;
                    end if;
                when 4 =>
                    if code = pwd3 then
                        cnt <= 0;
                        error <= '0';--正确
                        unlock <= '1';
                        state <= 0;
                    else
                        error <= '1';
                        cnt <= cnt + 1;
                        state <= 0;
                    end if;
                when others => null;
                end case;
                if cnt > 1 then
                    alarm <= '1';
                end if;
            elsif (mode = "10" or mode = "11") then --admin模式
                case state is
                when 1 =>
                    if CONV_INTEGER(code) = adminpwd(3) then
                        state <= 2;
                    else
                        error <= '1';--输入错误
                        state <= 0;
                    end if;
                when 2 =>
                    if CONV_INTEGER(code) = adminpwd(2) then
                        state <= 3;
                    else
                        error <= '1';
                        state <= 0;
                    end if;
                when 3 =>
                    if CONV_INTEGER(code) = adminpwd(1) then
                        state <= 4;
                    else
                        error <= '1';
                        state <= 0;
                    end if;
                when 4 =>
                    if CONV_INTEGER(code) = adminpwd(0) then
                        cnt <= 0;
                        error <= '0';
                        unlock <= '1';
                        alarm <= '0';--警报关闭
                        state <= 0; --正确
                    else
                        error <= '1';
                        state <= 0;
                    end if;
                when others => null;
                end case;
                if cnt > 1 then
                    alarm <= '1';
                end if;
            end if;
        end if;
    end process;
    
end bhv;
