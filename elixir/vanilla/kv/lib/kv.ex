defmodule KV do
  use Application

  require KV.Server

  @moduledoc """
  Documentation for KV.
  """

  @doc """
  Hello world.

  ## Examples

      iex> KV.hello()
      :world

  """
  def hello do
    :world
  end

  def start(_type, _args) do
    children = [
      {Task.Supervisor, name: KV.Server.TaskSupervisor},
      {Task, fn -> KV.Server.accept(4040) end}
    ]

    opts = [strategy: :one_for_one, name: KV.Server.Supervisor]
    Supervisor.start_link(children, opts)
  end
end
