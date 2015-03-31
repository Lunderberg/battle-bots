direction = "East"

function choose_action(state)
   if state:GetX() == 5 then
      direction = "West"
   elseif state:GetX() == 0 then
      direction = "East"
   end

   return Action("Move", direction)
end