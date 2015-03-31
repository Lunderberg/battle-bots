direction = "East"

function choose_action(state)
   default = Action("Move", "East")
   for i=1,30 do
      coroutine.yield()
   end

   default = Action("Move", "West")
   for i=1,30 do
      coroutine.yield()
   end
end