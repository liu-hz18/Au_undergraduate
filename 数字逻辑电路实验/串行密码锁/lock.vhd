-- 串行密码锁:支持设置密码、验证密码、三次输入限制、管理员模式 --
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity lock is
    port(
        code: in std_logic_vector(3 downto 0); --only for one digit
        mode: in std_logic_vector(1 downto 0); --mode: 1x:Admin, 00:set password, 01:check password
        clk, rst: in std_logic;
        unlock, error, alarm: buffer std_logic;
        checknum: out std_logic_vector(6 downto 0);--Show the input number, for debug;
        setnum: out std_logic_vector(6 downto 0)
    );
end lock;

architecture bhv of lock is
    component checkpwd
        port(
            clk, rst: in std_logic;
            mode: in std_logic_vector(1 downto 0);
            code: in std_logic_vector(3 downto 0);
            unlock, error, alarm: buffer std_logic;
            pwd0, pwd1, pwd2, pwd3: in std_logic_vector(3 downto 0);--4位16进制密码，由setpwd提供
            currentnum: out std_logic_vector(6 downto 0) -- 数码管输出当前数位
        );
    end component;
    component setpwd
        port(
            clk, rst: in std_logic;
            mode: in std_logic_vector(1 downto 0);
            code: in std_logic_vector(3 downto 0);
            pwd0, pwd1, pwd2, pwd3: out std_logic_vector(3 downto 0);
            currentnum: out std_logic_vector(6 downto 0)
        );
    end component;
    signal pwd0, pwd1, pwd2, pwd3: std_logic_vector(3 downto 0);
begin
    cpwd: checkpwd port map(clk=>clk, rst=>rst, mode=>mode, code=>code, unlock=>unlock, error=>error, alarm=>alarm,
            pwd0=>pwd0, pwd1=>pwd1, pwd2=>pwd2, pwd3=>pwd3, currentnum=>checknum);
    spwd: setpwd port map(clk=>clk, rst=>rst, mode=>mode, code=>code, 
            pwd0=>pwd0, pwd1=>pwd1, pwd2=>pwd2, pwd3=>pwd3, currentnum=>setnum);
end bhv;
