defmodule KvserverTest do
  use ExUnit.Case
  doctest Kvserver

  test "greets the world" do
    assert Kvserver.hello() == :world
  end
end
