class CreateEvents < ActiveRecord::Migration
  def change
    create_table :events do |t|
      t.string :name
      t.text :description
      t.references :schedule, index: true, foreign_key: true
      t.references :zone, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
