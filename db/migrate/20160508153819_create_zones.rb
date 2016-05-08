class CreateZones < ActiveRecord::Migration
  def change
    create_table :zones do |t|
      t.string :name
      t.text :description
      t.int :warm_up_mins

      t.timestamps null: false
    end
  end
end
